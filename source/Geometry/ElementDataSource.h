#ifndef ELEMENT_DATA_SOURCE_H_
#define ELEMENT_DATA_SOURCE_H_

#include "../DataTypes.h"

#include "PrimitiveType.h"

namespace bde{

  /**
  * Describes how vertices are combined for renderable primitives.
  *
  * @author Diego Jesus <diego.a.r.jz@gmail.com>
  */
  template<typename I>
  class CustomElementDataSource{
  private:
    I             *mElements;     ///< Array of elements.
    PrimitiveType mPrimitiveType; ///< The type of primitive.
    U32           mPrimitiveCount;///< Total number of primitives
    U32           mElementsCount; ///< Total number of elements.
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
    CustomElementDataSource(const I *elements,
                            const PrimitiveType &primitiveType,
                            const U32 &primitiveCount,
                            const U32 &elementCount){

      mElements = new I[ elementCount * sizeof(I) ];
      memcpy(mElements, elements, elementCount * sizeof(I) );

      mPrimitiveType  = primitiveType;
      mPrimitiveCount = primitiveCount;
      mElementsCount  = elementCount;
    }

    ~CustomElementDataSource(){
      delete []mElements;
    }

    /* ******************
    * Getters & Setters *
    * ******************/
    const I* GetElements() const{
      return mElements;
    }

    PrimitiveType GetPrimitiveType() const{
      return mPrimitiveType;
    }

    U32 GetPrimitiveCount() const{
      return mPrimitiveCount;
    }

    U32 GetElementsCount() const{
      return mElementsCount;
    }
  };

  template<typename I = U32>
  using CustomElementDataSourcePtr = std::shared_ptr<CustomElementDataSource<I>>;

  typedef CustomElementDataSource<U32> ElementDataSource;
  typedef CustomElementDataSourcePtr<U32> ElementDataSourcePtr;

} // namespace bde

#endif
