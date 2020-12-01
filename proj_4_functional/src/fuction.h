#include <iostream>
#include <memory>
#include <functional>

template <typename UnusedType>
class function;


template <typename ReturnType, typename ... Args>
struct function <ReturnType (Args ...)>
{
    
    typedef ReturnType signature_type (Args ...);
    
    function() : mInvoker() {}
    
    template <typename FunctionT>
    /// Uncomment this, and add corresponding assignment operator for `check4`
    //explicit
    function(FunctionT f)
    : mInvoker(new callable<FunctionT>(f))
    {
    }
    
    
    function(const function & other)
    : mInvoker(other.mInvoker->clone())
    {
    }
    
    function & operator = (const function & other)
    {
        mInvoker = other.mInvoker->clone();
    }
    
    ReturnType operator ()(Args ... args)
    {
        return mInvoker->invoke(args ...);
    }
    

    
    
    struct callable_base
    {
        callable_base()
        {
        }
        
        virtual ~callable_base()
        {
        }
        
        virtual ReturnType invoke(Args ... args) = 0;
        
        virtual std::auto_ptr<callable_base> clone() = 0;
        
        callable_base(const callable_base & );
        void operator = (const callable_base &);
    };
    
    
    typedef std::auto_ptr<callable_base> invoker_t;
    
    
    template <typename FunctionT>
    struct callable : public callable_base
    {
        callable(FunctionT func)
        : callable_base(),
        mFunction(func)
        {
            
        }
        
        virtual ReturnType invoke(Args ... args)
        {
            return mFunction(args ...);
        }
        
        
        virtual invoker_t clone()
        {
            return invoker_t(new callable(mFunction));
        }
        
        FunctionT mFunction;
    };
    
    
    invoker_t mInvoker;
};
