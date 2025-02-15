package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// Node represents a single element in the queue.
type Node struct {
	value interface{}
	next  *Node
}

// Queue represents a FIFO (first-in, first-out) queue implemented using a linked list.
type Queue struct {
	head *Node
	tail *Node
	size int
}

// New creates a new empty queue.
func NewQueue() *Queue {
	return &Queue{
		head: nil,
		tail: nil,
		size: 0,
	}
}

// Push adds an element to the end of the queue.
func (q *Queue) Push(item interface{}) {
	newNode := &Node{value: item, next: nil}
	if q.tail == nil {
		q.head = newNode
		q.tail = newNode
	} else {
		q.tail.next = newNode
		q.tail = newNode
	}
	q.size++
}

// Pop removes and returns the element at the front of the queue.
// Returns an error if the queue is empty.
func (q *Queue) Pop() (interface{}, error) {
	if q.IsEmpty() {
		return nil, fmt.Errorf("queue is empty")
	}
	elem := q.head.value
	q.head = q.head.next
	if q.head == nil {
		q.tail = nil
	}
	q.size--
	return elem, nil
}

// Peek returns the element at the front of the queue without removing it.
// Returns an error if the queue is empty.
func (q *Queue) Peek() (interface{}, error) {
	if q.IsEmpty() {
		return nil, fmt.Errorf("queue is empty")
	}
	return q.head.value, nil
}

// Size returns the number of elements in the queue.
func (q *Queue) Size() int {
	return q.size
}

// IsEmpty checks if the queue is empty.
func (q *Queue) IsEmpty() bool {
	return q.size == 0
}

func main() {
	queue := NewQueue()
	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("Queue operations: push <value>, pop, peek, size, exit")

	for {
		fmt.Print("Enter command: ")
		scanner.Scan()
		input := scanner.Text()

		if input == "exit" {
			fmt.Println("Exiting...")
			break
		}

		parts := strings.Fields(input)
		if len(parts) == 0 {
			continue
		}

		command := parts[0]

		switch command {
		case "push":
			if len(parts) < 2 {
				fmt.Println("Usage: push <value>")
				continue
			}
			value := parts[1]
			queue.Push(value)
			fmt.Printf("Pushed: %s\n", value)
		case "pop":
			value, err := queue.Pop()
			if err != nil {
				fmt.Println(err)
			} else {
				fmt.Printf("Popped: %v\n", value)
			}
		case "peek":
			value, err := queue.Peek()
			if err != nil {
				fmt.Println(err)
			} else {
				fmt.Printf("Front: %v\n", value)
			}
		case "size":
			fmt.Printf("Size: %d\n", queue.Size())
		default:
			fmt.Println("Unknown command")
		}
	}
}
