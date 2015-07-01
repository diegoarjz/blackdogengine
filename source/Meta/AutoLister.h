#ifndef AUTOLISTER_H_
#define AUTOLISTER_H_

namespace bde {

    /**
     * Automatically places instances of subclasses in a linked list.
     *
     * On destruction, it doesn't remove any instance from the list,
     * therefore, the list is left in an invalid state.
     *
     * It is meant to be used by static instances, namely instances
     * of MetaVariable and MetaFunction, keeping a record of all 
     * registered variables and functions.
     */
    template<typename T>
    class AutoLister {
      private:
        T *mNext;

      public:
        AutoLister() {
            mNext = Head();
            Head() = static_cast<T *>(this);
        }

        T *Next() {
            return mNext;
        }
        const T *Next() const {
            return mNext;
        }

        static T *&Head() {
            static T *p = 0;
            return p;
        }
    }; // class AutoLister

} // namespace bde
#endif
