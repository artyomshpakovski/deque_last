#ifndef DEQUE_H_
#define DEQUE_H_

#include <vector>
#include <cassert>
#include <iostream>

namespace containers {

    template<class T>
    class deque {
    public:
        struct Object {
        public:
            T value;
            friend class deque;

        private:
            Object* ptr_next{ nullptr };
            Object* ptr_previous{ nullptr };
            Object() = default;
            explicit Object(const T& value) : value(value) {}
            explicit Object(T&& new_value) : value(std::move(new_value)) {}
            explicit Object(Object* object) : value(object->value) {}
        };

        deque() = default;


        deque(const deque& deq) {
            Object* current = deq.head_;
            while (current != nullptr) {
                PushBack(current->value);
                current = current->ptr_next;
            }
        }

        deque(deque&& deq) noexcept :
            head_(std::move(deq.head_)),
            tail_(std::move(deq.tail_)),
            size_(std::move(deq.size_)) {
            deq.head = nullptr;
            deq.tail = nullptr;
            deq.size = 0;
        }

        ~deque() {
            Clear();
        }

        void Clear() {
            while (!IsEmpty()) {
                PopBack();
            }
        }

        deque& operator=(const deque& deq) {
            if (this == &deq) {
                return *this;
            }
            Clear();
            Object* current = deq.head_;
            while (current != nullptr) {
                PushBack(current->value);
                current = current->ptr_next;
            }
            return (*this);
        }

        deque& operator=(deque&& deq) {
            if (this == &deq) {
                return *this;
            }
            Clear();
            head_ = deq.head_;
            tail_ = deq.tail_;
            size_ = deq.size_;
            deq.head_ = nullptr;
            deq.tail_ = nullptr;
            deq.size_ = 0;
            return (*this);
        }

        int Size() const {
            return size_;
        }

        bool IsEmpty() const {
            return (size_ == 0);
        }

        std::vector<T> ToVector() const {
            std::vector<T> result;
            Object* current = head_;
            while (current != nullptr) {
                result.emplace_back(current->value);
                current = current->ptr_next;
            }
            return result;
        }

        Object* Front() {
            return head_;
        }

        const Object* Front() const {
            return head_;
        }

        Object* Back() {
            return tail_;
        }

        const Object* Back() const {
            return tail_;
        }

        void PushBack(const T& value) {
            if (IsEmpty()) {
                size_++;
                head_ = new Object(value);
                tail_ = head_;
            }
            else {
                size_++;
                Object* new_value = new Object(value);
                tail_->ptr_next = new_value;
                new_value->ptr_previous = tail_;
                tail_ = new_value;
            }
        }

        void PushFront(const T& value) {
            if (IsEmpty()) {
                size_++;
                head_ = new Object(value);
                tail_ = head_;
            }
            else {
                size_++;
                Object* new_value = new Object(value);
                head_->ptr_previous = new_value;
                new_value->ptr_next = head_;
                head_ = new_value;
            }
        }

        void PushBack(T& value) {
            if (IsEmpty()) {
                size_++;
                head_ = new Object(std::move(value));
                tail_ = head_;
            }
            else {
                size_++;
                Object* new_value = new Object(std::move(value));
                tail_->ptr_next = new_value;
                new_value->ptr_previous = tail_;
                tail_ = new_value;
            }
        }

        void PushFront(T& value) {
            if (IsEmpty()) {
                size_++;
                head_ = new Object(std::move(value));
                tail_ = head_;
            }
            else {
                size_++;
                Object* new_value = new Object(std::move(value));
                head_->ptr_previous = new_value;
                new_value->ptr_next = head_;
                head_ = new_value;
            }
        }

        void PopBack() {
            assert(!IsEmpty());
            if (size_ == 1) {
                delete head_;
                head_ = nullptr;
                tail_ = nullptr;
                size_--;
                return;
            }
            Object* new_tail = tail_->ptr_previous;
            delete tail_;
            tail_ = new_tail;
            new_tail->ptr_next = nullptr;
            size_--;
        }

        void PopFront() {
            assert(!IsEmpty());
            if (size_ == 1) {
                tail_ = nullptr;
            }
            Object* new_head(head_->ptr_next);
            delete head_;
            head_ = new_head;
            size_--;
        }

        void Erase(Object* element) {
            assert(!IsEmpty());
            if (element == head_) {
                PopFront();
                return;
            }
            if (element == tail_) {
                PopBack();
                return;
            }
            element->ptr_previous->ptr_next = element->ptr_next;
            element->ptr_next->ptr_previous = element->ptr_previous;
            delete element;
            size_--;
        }

        /*Object* operator[](int index) {
            assert(index <= size_ && index >= 0);
            int i = 0;
            Object* current = head_;
            while (i != index) {
                i++;
                current = current->ptr_next;
            }
            return current;
        }*/

        void WriteToConsoleFromHeadToTail() {
            int i = 0;
            Object* current = head_;
            while (i < Size())
            {
                i++;
                std::cout << current->value << " ";
                current = current->ptr_next;
            }
            delete current;
            std::cout << std::endl;
        }

        void WriteToConsoleFromTailToHead() {
            int i = 0;
            Object* current = tail_;
            while (i < Size())
            {
                i++;
                std::cout << current->value << " ";
                current = current->ptr_previous;
            }
            delete current;
            std::cout << std::endl;
        }

        friend std::ostream& operator << (std::ostream& out, const Object& deq)
        {
            out << deq->value << " ";
            return out;
        }

    private:
        Object* head_{ nullptr };
        Object* tail_{ nullptr };
        size_t size_{ 0 };
    };

}

#endif // DEQUE_H_
