package main

import (
	"fmt"
)

// Структура узла очереди
type Node struct {
	value interface{} // значение, хранимое в узле
	next  *Node       // указатель на следующий узел
}

// Структура самой очереди
type Queue struct {
	head *Node // указатель на первый элемент очереди
	tail *Node // указатель на последний элемент очереди
	size int   // размер очереди (количество элементов)
}

// Функция для создания новой очереди
func NewQueue() *Queue {
	return &Queue{
		head: nil, // в начале голова пуста
		tail: nil, // в начале хвост пуст
		size: 0,   // размер очереди равен 0
	}
}

// Метод для добавления элемента в очередь
func (q *Queue) Push(item interface{}) {
	newNode := &Node{value: item, next: nil} // создаём новый узел с переданным значением
	if q.tail == nil {                       // если очередь пустая
		q.head = newNode // новый элемент становится и головой, и хвостом
		q.tail = newNode
	} else {
		q.tail.next = newNode // добавляем новый элемент в конец очереди
		q.tail = newNode      // обновляем хвост
	}
	q.size++ // увеличиваем размер очереди
}

// Метод для удаления и получения элемента из очереди
func (q *Queue) Pop() (interface{}, error) {
	if q.IsEmpty() { // если очередь пуста
		return nil, fmt.Errorf("queue is empty") // возвращаем ошибку
	}
	elem := q.head.value // получаем значение первого элемента
	q.head = q.head.next // сдвигаем голову на следующий элемент
	if q.head == nil {   // если очередь стала пустой
		q.tail = nil // хвост тоже становится пустым
	}
	q.size--         // уменьшаем размер очереди
	return elem, nil // возвращаем значение элемента
}

// Метод для просмотра первого элемента без его удаления
func (q *Queue) Peek() (interface{}, error) {
	if q.IsEmpty() { // если очередь пуста
		return nil, fmt.Errorf("queue is empty") // возвращаем ошибку
	}
	return q.head.value, nil // возвращаем значение первого элемента
}

// Метод для получения размера очереди
func (q *Queue) Size() int {
	return q.size // возвращаем размер очереди
}

// Метод для проверки, пуста ли очередь
func (q *Queue) IsEmpty() bool {
	return q.size == 0 // если размер равен 0, очередь пуста
}
