//
// Created by chenda on 2019/8/1.
//

#ifndef CORENOTE_ITERATOR_H
#define CORENOTE_ITERATOR_H

template <class E>
class Iterator{
public:
    virtual bool hasNext()=0;
    virtual E next()=0;
    virtual void remove()=0;
};

#endif //CORENOTE_ITERATOR_H
