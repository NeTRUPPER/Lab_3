package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestQueuePushAndPop(t *testing.T) {
	q := NewQueue()

	// Добавляем элементы в очередь
	q.Push("first")
	q.Push("second")
	q.Push("third")

	// Проверяем порядок извлечения (FIFO)
	val, err := q.Pop()
	assert.NoError(t, err)
	assert.Equal(t, "first", val)

	val, err = q.Pop()
	assert.NoError(t, err)
	assert.Equal(t, "second", val)

	val, err = q.Pop()
	assert.NoError(t, err)
	assert.Equal(t, "third", val)

	// Очередь должна быть пустой
	assert.True(t, q.IsEmpty())
}

func TestQueuePeek(t *testing.T) {
	q := NewQueue()
	q.Push("only")

	val, err := q.Peek()
	assert.NoError(t, err)
	assert.Equal(t, "only", val)

	// Убедимся, что элемент остался в очереди
	assert.False(t, q.IsEmpty())

	val, err = q.Pop()
	assert.NoError(t, err)
	assert.Equal(t, "only", val)

	assert.True(t, q.IsEmpty())
}

func TestQueueSize(t *testing.T) {
	q := NewQueue()
	assert.Equal(t, 0, q.Size())

	q.Push(1)
	q.Push(2)
	assert.Equal(t, 2, q.Size())

	q.Pop()
	assert.Equal(t, 1, q.Size())

	q.Pop()
	assert.Equal(t, 0, q.Size())
}

func TestQueueEmptyPop(t *testing.T) {
	q := NewQueue()

	_, err := q.Pop()
	assert.Error(t, err)
	assert.Equal(t, "queue is empty", err.Error())
}

func TestQueueEmptyPeek(t *testing.T) {
	q := NewQueue()

	_, err := q.Peek()
	assert.Error(t, err)
	assert.Equal(t, "queue is empty", err.Error())
}
