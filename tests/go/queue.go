package main

import (
	"bufio"
	"encoding/gob"
	"fmt"
	"os"
	"strconv"
	"strings"
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
		tail: nil, // в нач                            але хвост пуст
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

// Сериализация в текстовый файл
func (q *Queue) SerializeToText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	current := q.head
	for current != nil {
		fmt.Fprintln(writer, current.value)
		current = current.next
	}
	return writer.Flush()
}

// Десериализация из текстового файла
func (q *Queue) DeserializeFromText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		value := scanner.Text()
		if num, err := strconv.Atoi(strings.TrimSpace(value)); err == nil {
			q.Push(num) // Если число, добавляем как int
		} else {
			q.Push(value) // Если строка, добавляем как string
		}
	}
	return scanner.Err()
}

// Сериализация в бинарный файл
func (q *Queue) SerializeToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	encoder := gob.NewEncoder(file)
	return encoder.Encode(q)
}

// Десериализация из бинарного файла
func (q *Queue) DeserializeFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	decoder := gob.NewDecoder(file)
	return decoder.Decode(q)
}

func main() {
	q := NewQueue()
	q.Push(10)
	q.Push(20)
	q.Push(30)

	q.SerializeToText("queue.txt")
	newQueue := NewQueue()
	newQueue.DeserializeFromText("queue.txt")

	q.SerializeToBinary("queue.bin")
	binaryQueue := NewQueue()
	binaryQueue.DeserializeFromBinary("queue.bin")
}
