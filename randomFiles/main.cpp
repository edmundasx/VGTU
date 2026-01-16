#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <conio.h>
#include <vector>
#include <cmath>
#include <Windows.h>
using namespace std;

struct TaskQueue {
    queue<int> tasks;
    HANDLE mutex;
    HANDLE tasksAvailable;
    int maxPrime = INT_MIN;
    int minPrime = INT_MAX;
};


bool isPrime(int num);
void producer(TaskQueue *taskQueue);
void consumer(LPVOID lpParam);
void threadController(TaskQueue* taskQueue, vector<HANDLE>* hConsumers);

int main()
{
    TaskQueue taskQueue;
    vector<HANDLE> hConsumers;
    taskQueue.mutex = CreateMutex(NULL, FALSE, NULL);
    taskQueue.tasksAvailable = CreateSemaphore(NULL, 0, INT_MAX, NULL);

    HANDLE hProducer = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)producer, &taskQueue, 0, NULL);
    hConsumers.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer, &taskQueue, 0, NULL));
    hConsumers.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer, &taskQueue, 0, NULL));
    hConsumers.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer, &taskQueue, 0, NULL));
    hConsumers.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer, &taskQueue, 0, NULL));
    threadController(&taskQueue, &hConsumers);

        WaitForSingleObject(hProducer, INFINITE);

    for (int i = 0; i < hConsumers.size(); ++i) {
        TerminateThread(hConsumers[i], INFINITE);
        CloseHandle(hConsumers[i]);
    }

    CloseHandle(hProducer);
    CloseHandle(taskQueue.mutex);

    return 0;
}
bool isPrime(int num)
{
    if (num <= 1)
    {
        return false;
    }

    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

void producer(TaskQueue *taskQueue)
{
    string filePath = "C:/Users/user/Desktop/SiteminisPorgramavimasLD3/rand_files/";
    string fileName = "file";
    string fileExtension = ".txt";
    int num;

    for (int i = 1; i <= 1000; i++)
    {
        ifstream file(filePath + fileName + to_string(i) + fileExtension);
        if (file.is_open())
        {
            cout << "Reading file: " << fileName + to_string(i) + fileExtension << endl;
            while (file >> num)
            {
                WaitForSingleObject(taskQueue->mutex, INFINITE);
                taskQueue->tasks.push(num);
                ReleaseMutex(taskQueue->mutex);
                ReleaseSemaphore(taskQueue->tasksAvailable, 1, NULL);
            }
        }
        cout << "Current Max Prime number found: " << taskQueue->maxPrime << endl;
        cout << "Current Min Prime number found: " << taskQueue->minPrime << endl;
    }
}

void consumer(LPVOID lpParam)
{
    TaskQueue* taskQueue = (TaskQueue*)lpParam;
    int task;
    while (true) {
        WaitForSingleObject(taskQueue->tasksAvailable, INFINITE);
        WaitForSingleObject(taskQueue->mutex, INFINITE);
        task = taskQueue->tasks.front();
        taskQueue->tasks.pop();
        ReleaseMutex(taskQueue->mutex);
        if (isPrime(task)) {
            if (taskQueue->maxPrime < task)
            {
                taskQueue->maxPrime = task;
            }
            else if (taskQueue->minPrime > task)
            {
                taskQueue->minPrime = task;
            }
        }
    }
}

void threadController(TaskQueue* taskQueue, vector<HANDLE>* hConsumers)
{
    while (true) {
        if (_kbhit()) {
            char input = _getch();
            if (input == '+') {
                hConsumers->push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer, taskQueue, 0, NULL));
                cout << "Thread added. Total number of threads: " << hConsumers->size() << endl;
            }
            else if (input == '-' && !hConsumers->empty()) {
                TerminateThread(hConsumers->back(), INFINITE);
                CloseHandle(hConsumers->back());
                hConsumers->pop_back();
                cout << "Thread removed. Total number of threads: " << hConsumers->size() << endl;            }
        }
        Sleep(2000);
    }
}
