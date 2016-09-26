//
//  slist.h
//  BTP_Lab3
//
//  Created by Fateh Sandhu on 2016-09-23.
//  Copyright © 2016 Fateh Sandhu. All rights reserved.
//

#include <iostream>
using namespace std;

template <typename T>
class SList{
    struct Node{
        T data_;
        Node* next_;
        Node(const T& data,Node* next=nullptr){
            data_=data;
            next_=next;
        }
    };
    Node* head_;
    Node* tail_;
public:
    SList(){
        head_=tail_=nullptr;
    }
    void push_front(const T& data){
        Node* temp=new Node(data,head_);
        if(!head_){
            tail_=temp;
        }
        head_=temp;
        
        
    }
    
    //Fateh Sandhu - editor
    void push_back(const T& data){
        Node* temp=new Node(data);
        if(head_){
            if(head_ != tail_){
                tail_->next_ = temp;
                tail_ = temp;
            }
            else{
                tail_ = temp;
                head_->next_ = tail_;
            }
        }
        else
            tail_ = head_ = temp;
        
    }
    
    //Fateh Sandhu - editor
    void pop_front(){
        if(head_){
            if(head_ != tail_){
                Node* temp = head_->next_;
                delete head_;
                head_ = temp;
            }
            else
            {
                delete head_;
                delete tail_;
                head_  = tail_ = nullptr;
            }
        }
    }
    
    
    void pop_back(){
        if(head_){
            if(head_!=tail_){
                Node* last=tail_;
                Node* secondLast=head_;//=tail_->prev_;
                while(secondLast->next_!=tail_){
                    secondLast=secondLast->next_;
                }
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
