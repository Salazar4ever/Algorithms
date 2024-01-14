#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* data;
    size_t head;
    size_t tail;
};

Queue *queue_create()
{
    Queue* tmp = new Queue;
    tmp->data = vector_create();
    tmp->head = tmp->tail = 0;
    return tmp;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (!vector_size(queue->data) || !((queue->tail - queue->head + vector_size(queue->data)) % vector_size(queue->data)))
    {
        Vector* newData = vector_create();
        vector_resize(newData, (vector_size(queue->data) + 1) * 2);

        size_t i, j = 0;
        if (vector_size(queue->data))
        {
            for (i = queue->head; i + 1 != queue->tail; i++)
            {
                i %= vector_size(queue->data);
                vector_set(newData, j++, vector_get(queue->data, i));
            }
            vector_set(newData, j++, vector_get(queue->data, i));
        }
        queue->tail = j;
        queue->head = 0;
        vector_delete(queue->data);
        queue->data = newData;
    }
    queue->tail %= vector_size(queue->data);
    vector_set(queue->data, queue->tail++, data);
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->data, queue->head);
}

void queue_remove(Queue *queue)
{
    queue->head++;
}

bool queue_empty(const Queue *queue)
{
    return (queue->tail - queue->head == 0);
}
