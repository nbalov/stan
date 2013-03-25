#ifndef __STAN__AGRAD__CHAINABLE_HPP__
#define __STAN__AGRAD__CHAINABLE_HPP__

#include <stan/agrad/var_stack.hpp>

namespace stan {
  namespace agrad {

    /**
     * Abstract base class for variable implementations that handles
     * memory management and applying the chain rule.
     */
    class chainable {

    public:

      /**
       * Construct a chainable object.  The implementation
       * in this abstract base class is a no-op.
       */
      chainable() { }

      /**
       * Chainables are not destructible and should go on the function
       * call stack or be allocated with operator new.
       */
      ~chainable() { 
        // handled automatically
      }

      /**
       * Apply the chain rule to this variable based on the variables
       * on which it depends.  The base implementation in this class
       * is a no-op. 
       */
      virtual void chain() {
      }

      /**
       * Initialize this chainable's adjoint value to make it
       * the dependent variable in a gradient calculation. 
       */
      virtual void init_dependent() {
      }

      /**
       * Set the value of the adjoint for this chainable
       * to its initial value.
       */
      virtual void set_zero_adjoint() {
      }

      /**
       * Allocate memory from the underlying memory pool.  This memory is
       * is managed by the gradient program and will be recovered as a whole.
       * Classes should not be allocated with this operator if they have
       * non-trivial destructors.
       *
       * @param nbytes Number of bytes to allocate.
       * @return Pointer to allocated bytes.
       */
      static inline void* operator new(size_t nbytes) {
        return memalloc_.alloc(nbytes);
      }
    };

  }
}
#endif
