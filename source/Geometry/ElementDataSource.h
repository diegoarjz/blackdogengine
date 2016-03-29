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
     * The ElementDataSource contains a buffer of indices a vertex buffer.
     * Together with the primitive type it is, then, possible to describe
     * how primitives are put together from a buffer of vertices.
     *
     * Each ElementDataSource owns a buffer of indices that is copied from
     * an user specified buffer during construction. This buffer is deleted
     * during destruction. Therefore, the original buffer can be deleted
     * if the user desires.
     */
    class ElementDataSource {
      private:
        U32 *mElements;     ///< Array of elements.
        PrimitiveType mPrimitiveType; ///< The type of primitive.
        U32 mPrimitiveCount;///< Total number of primitives
        U32 mElementsCount; ///< Total number of elements.
        BindingInfoPtr mBindingInfo;   ///< The binding on the GPU
      public:
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
        /**
         * Deletes the index buffer.
         */
        ~ElementDataSource();

        /**
         * Returns a pointer to the index buffer.
         */
        const U32 *GetElements() const;
        /**
         * Returns the type of primitives constructed.
         */
        PrimitiveType GetPrimitiveType() const;
        /**
         * Returns the number of primiives to be created.
         */
        U32 GetPrimitiveCount() const;
        /**
         * Returns the number of elements in the index buffer.
         */
        U32 GetElementsCount() const;
        /**
         * Returns the size in bytes of the index buffer.
         */
        U32 GetSizeInBytes()const;
        BindingInfoPtr GetBindingInfo();
        void SetBindingInfo(BindingInfoPtr bi);

    }; // class ElementDataSource

    /// Type for a shared, smart pointer to an ElementDataSource.
    typedef std::shared_ptr<ElementDataSource> ElementDataSourcePtr;

} // namespace bde

#else
namespace bde {
    class ElementDataSource;
    typedef std::shared_ptr<ElementDataSource> ElementDataSourcePtr;
}
#endif
