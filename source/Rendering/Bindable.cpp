#include "Bindable.h"

namespace bde {
    
    BindingInfoPtr Bindable::GetBindingInfo() const{
        return mBindingInfo;
    }
    
    void Bindable::SetBindingInfo(BindingInfoPtr bi){
        mBindingInfo = bi;
    }
}