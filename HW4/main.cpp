#include <pthread.h>
#include <cstdio>
#include <iostream>
#include <semaphore.h>
#include <unistd.h>
#include <cstring>

// Глобальные переменные, где хранится число людей в галерее.
// А так же мьютексы и семафоры для работы с программой
int peopleInGallery = 0;
pthread_mutex_t mutex;
sem_t semaphore[5];
FILE *out = nullptr;

// Методы, где посетитель по порядку обходит все картины
void *visitImage1() {
    sem_wait(&semaphore[0]);
    sleep(1);
    std::cout << "Looks at the picture 1 \n";
    fprintf(out, "%s", "Looks at the picture 1 \n");
    sem_post(&semaphore[0]);
}

void *visitImage2() {
    sem_wait(&semaphore[1]);
    sleep(1);
    std::cout << "Looks at the picture 2 \n";
    fprintf(out, "%s", "Looks at the picture 2 \n");
    sem_post(&semaphore[1]);
}

void *visitImage3() {
    sem_wait(&semaphore[2]);
    sleep(1);
    std::cout << "Looks at the picture 3 \n";
    fprintf(out, "%s", "Looks at the picture 3 \n");
    sem_post(&semaphore[2]);
}

void *visitImage4() {
    sem_wait(&semaphore[3]);
    sleep(1);
    std::cout << "Looks at the picture 4 \n";
    fprintf(out, "%s", "Looks at the picture 4 \n");
    sem_post(&semaphore[3]);
}

void *visitImage5() {
    sem_wait(&semaphore[4]);
    sleep(1);
    std::cout << "Looks at the picture 5 \n";
    fprintf(out, "%s", "Looks at the picture 5 \n");
    sem_post(&semaphore[4]);
}

void *visitAllImages(void *args) {
    // Посетитель проходит все 5 картин, прежде чем выйти
    std::cout << "Come to the gallery \n";
    fprintf(out, "%s", "Come in gallery \n");

    visitImage1();
    visitImage2();
    visitImage3();
    visitImage4();
    visitImage5();

    std::cout << "Left the gallery \n";
    fprintf(out, "%s", "Left the gallery \n");
    // Человек выходит из очереди, мьютекс чтобы корректно вычесть
    pthread_mutex_lock(&mutex);
    --peopleInGallery;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv) {
    pthread_mutex_t mut;
    FILE *in = nullptr;
    int counterVisitor;
    if (argc == 1) {
        std::cin >> counterVisitor;
        out = fopen("tests/output.txt", "w");
    } else if (argc == 2 && strcmp(argv[1], "r") == 0) {
        counterVisitor = rand() % 50 + 20;
        std::cout << "Count visitors:" << counterVisitor << "\n";
        out = fopen("tests/output.txt", "w");
    } else if (argc == 3) {
        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");
        if (in == nullptr) {
            std::cout << "incorrect file\n";
            return -1;
        }
        fscanf(in, "%d \n", &counterVisitor);
        fclose(in);

    } else if (argc == 2) {
        counterVisitor = std::stoi(argv[1]);
        out = fopen("tests/output.txt", "w");
    }
    int counterFinishVisitors = 0;

    size_t size_semaphore = 5;
    // Инициализируем мьютекс
    pthread_mutex_init(&mutex, nullptr);
    pthread_mutex_init(&mut, nullptr);

    for (int i = 0; i < size_semaphore; ++i) {
        // инициализация семафора, который принимает до 10 потоков (10 человек макс в очереди на картину)
        sem_init(&semaphore[i], 0, 10);
    }

    pthread_t th[counterVisitor];
    while (counterFinishVisitors != counterVisitor) {
        if (peopleInGallery < 50) {
            pthread_mutex_lock(&mut);
            if (pthread_create(&th[counterFinishVisitors++], nullptr, visitAllImages, nullptr) != 0) {
                perror("Fail create");
                return 1;
            }
            ++peopleInGallery;
            pthread_mutex_unlock(&mut);
        }
    }

    // Ждем здесь все потоки
    for (int i = 0; i < counterVisitor; ++i) {
        if (pthread_join(th[i], nullptr) != 0) {
            std::cout << "error";
            return 2;
        }
    }
    // Уничтожаем семафоры
    for (int i = 0; i < size_semaphore; ++i) {
        sem_destroy(&semaphore[i]);
    }
    // Уничтожаем мьютекс
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mut);
    fclose(out);
    return 0;
}