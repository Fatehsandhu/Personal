//
//  dlisttester.hpp
//  BTP_Lab3
//
//  Created by Fateh Sandhu on 2016-09-23.
//  Copyright © 2016 Fateh Sandhu. All rights reserved.
//
#include <iostream>
using namespace std;

template <typename T>
class DList{
    struct Node{
        T data_;
        Node* next_;
        Node* prev_;
        
        Node(const T& data,Node* next=nullptr,Node* prev=nullptr){
            data_=data;
            next_=next;
            prev_=prev;
        }
    };
    Node* head_;
    Node* tail_;
    
public:
    DList(){
        head_=tail_=nullptr;
    }
    void push_front(const T& data){
        Node* temp=new Node(data, head_);
        if(head_){
            head_->prev_=temp;
        }
        else{
            tail_=temp;
        }
        head_=temp;
        
    }
    
    
    //Fateh Sandhu- editor
    void push_back(const T& data){
        Node* temp=new Node(data, nullptr, tail_);
        if(head_){
            tail_->next_ = temp;
        }
        else{
            head_ = temp;
            head_->next_ = tail_;
        }
        
        tail_ = temp;
        
    }
    
    
    //Fateh Sandhu - editor
    void pop_front(){
        if(head_){
           if( head_ != tail_){
            head_->next_->prev_ = nullptr;
            delete head_;
            head_ = head_->next_;
           }
           else{
               delete tail_;
               delete head_;
               head_=tail_=nullptr;
           }
        }
    }
    
    void pop_back(){
        if(head_){
            if(head_!=tail_){
                Node* last=tail_;
                Node* secondLast=tail_->prev_;
                secondLast->next_=nullptr;
                delete last;
                tail_=secondLast;
            }
            else{
                delete head_;
                head_=tail_=nullptr;
            }
        }
        
    }
    void print() const{
        Node* it=head_;
        while(it){
            cout << it->data_ << endl;
            it=it->next_;
        }
    }
};
