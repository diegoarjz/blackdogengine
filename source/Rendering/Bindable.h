#ifndef ____Bindable__
#define ____Bindable__

#include "BindingInfo.h"

namespace bde {
    /**
     * Provides methods to bind to the graphics memory.
     */
    class Bindable{
    private:
        BindingInfoPtr mBindingInfo;
    public:
        BindingInfoPtr GetBindingInfo() const;
        void SetBindingInfo(BindingInfoPtr bi);
    }; // class Bindable;
} // namespace bde
#endif /* defined(____Bindable__) */
