#include "node.h"
using namespace std;


Node::Node(){}
Node::Node(const Date& data)
    :data_(data){
}
Node::Node(const string& event)
    :event_(event){
}

bool EmptyNode::Evaluate(const Date& data,const string& event) const{
    return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp,Date data)
    :cmp_(cmp)
    ,Node(data){
}

bool DateComparisonNode::Evaluate(const Date& date,const string& s) const{
    if (cmp_ == Comparison::Equal) {
        return  date == data_;
    } else if (cmp_ == Comparison::Greater) {
    	return  data_ < date;
    } else if (cmp_ == Comparison::GreaterOrEqual) {
    	return data_ < date || data_ == date;
    } else if (cmp_ == Comparison::LessOrEqual) {
    	return date < data_ || date == data_;
    } else if (cmp_ == Comparison::NotEqual) {
    	return data_ != date;
    } else if (cmp_ == Comparison::Less) {
    	return date < data_;
    }
    return false;
}

EventComparisonNode::EventComparisonNode(Comparison cmp, string value)
    :cmp_(cmp)
    ,Node(value){
}

bool EventComparisonNode::Evaluate(const Date& data,const string& event) const {
    if (cmp_ == Comparison::Equal) {
        return event == event_;
    } else if (cmp_ == Comparison::Greater) {
        return event_ < event;   //
    } else if (cmp_ == Comparison::GreaterOrEqual) {
        return event_ < event || event_ == event;
    } else if (cmp_ == Comparison::LessOrEqual) {
        return event < event_ || event == event_;
    } else if (cmp_ == Comparison::NotEqual) {
        return event_ != event;
    } else if (cmp_ == Comparison::Less) {
        return event < event_;
    }
    return false;
}

LogicalOperationNode::LogicalOperationNode (const LogicalOperation& op,
	const shared_ptr<Node>& left,
    const shared_ptr<Node>& right)
	:op_(op)
	,left_(left)
	,right_(right){
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& s) const{
    if (op_ == LogicalOperation::And) {
        return left_->Evaluate(date, s) && right_->Evaluate(date, s);
    } else if (op_ == LogicalOperation::Or) {
        return left_->Evaluate(date, s) || right_->Evaluate(date, s);
    }
    return false;
}






