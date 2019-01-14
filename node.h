#pragma once

#include <memory>
#include <iostream>
#include "date.h"

using namespace std;

enum class Comparison{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation{
    Or,
    And
};

class Node {
public:
    Node();
    Node(const Date& data);
    Node(const string& event);
    virtual bool Evaluate(const Date& data,const string& event) const=0;
protected:
    Date data_;
    string event_;
};
class EmptyNode: public Node{
public:
    bool Evaluate(const Date& data,const string& event) const override;
};

class DateComparisonNode: public Node{
public:
    DateComparisonNode(Comparison cmp,Date data);

    bool Evaluate(const Date& data,const string& event) const override;

private:
    Comparison cmp_;
};

class EventComparisonNode: public Node{
public:
    EventComparisonNode(Comparison cmp, string value);

    bool Evaluate(const Date& data,const string& event) const override;
private:
    Comparison cmp_;
};

class LogicalOperationNode: public Node{
public:
    LogicalOperationNode (const LogicalOperation& op,
                          const shared_ptr<Node>& left,
                          const shared_ptr<Node>& right);
    bool Evaluate(const Date& date,const string& s) const override;
private:
    LogicalOperation op_;
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
};
