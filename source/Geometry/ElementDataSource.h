#ifndef ELEMENT_DATA_SOURCE_H_
#define ELEMENT_DATA_SOURCE_H_

#include <memory>

#include "../DataTypes.h"

#include "../Rendering/BindingInfo.h"
#include "PrimitiveType.h"

namespace bde {

    /**
     * Describes how vertices are combined for renderable primitives.
     *
     * @author Diego Jesus <diego.a.r.jz@gmail.com>
     */
    class ElementDataSource {
      private:
        U32             *mElements;     ///< Array of elements.
        PrimitiveType   mPrimitiveType; ///< The type of primitive.
        U32             mPrimitiveCount;///< Total number of primitives
        U32             mElementsCount; ///< Total number of elements.
        BindingInfoPtr  mBindingInfo;   ///< The binding on the GPU
      public:

        /* ***************************
         * Construction & Destruction *
         * ***************************/
        /**
         * Constructor taking an array of elements, the type of primitives,
         * the number of primitives and the number of elements.
         *
         * Creates a copy of the array of elements. The passed array can, then,
         * be safely deleted outside.
         */
        ElementDataSource(const U32 *elements,
                          const PrimitiveType &primitiveType,
                          const U32 &primitiveCount,
                          const U32 &elementCount);
        ~ElementDataSource();

        /* ******************
         * Getters & Setters *
         * ******************/
        const U32 *GetElements() const;
        PrimitiveType GetPrimitiveType() const;
        U32 GetPrimitiveCount() const;
        U32 GetElementsCount() const;
        U32 GetSizeInBytes()const;
        BindingInfoPtr GetBindingInfo();
        void SetBindingInfo(BindingInfoPtr bi);

    }; // class ElementDataSource

    typedef std::shared_ptr<ElementDataSource> ElementDataSourcePtr;

} // namespace bde

#else
namespace bde {
    class ElementDataSource;
    typedef std::shared_ptr<ElementDataSource> ElementDataSourcePtr;
}
#endif
