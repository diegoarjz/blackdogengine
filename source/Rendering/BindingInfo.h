#ifndef BINDINGINFO_H_
#define BINDINGINFO_H_

#include <ostream>
#include <memory>

#include "../DataTypes.h"

namespace bde {
    /**
     * This class contains information about the binding between some structure and
     * its representation in the graphics card.
     */
    class BindingInfo {
      private:
        /// The identifier in the graphics card.
        U32 mBindingID;

        /// Indicates if it is bound in the graphics card.
        bool mBound;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        BindingInfo(const U32 &id);
        ~BindingInfo();

        /* *******************
         * Getters & Setters *
         * ******************/
        /**
         * Returns the binding id.
         * @return Binding id.
         */
        U32 GetBindingID() const;

        /**
         * Returns wether it is bound in the hardware.
         * @return True if bound on the hardware, false otherwise.
         */
        bool IsBound() const;

        /**
         * Indicate that it has been bound in the hardware and what id it has.
         * @param id [in] The id in the hardware.
         * @param type [in] The purpose that it has.
         */
        void Bind();

        /**
         * Indicate that it has been unbound from the hardware.
         */
        void Unbind();

        /**
         * Output operation, mainly for debugging purposes.
         * @param stream [in] Output stream.
         * @param o [in] BindingInfo to output.
         * @return The stream parameter, allowing to chain operations.
         */
        friend std::ostream &operator<< (std::ostream &stream, const BindingInfo &o);
    }; // class BindingInfo

    typedef std::shared_ptr<BindingInfo> BindingInfoPtr;
    typedef std::weak_ptr<BindingInfo> BindingInfoWeakPtr;
} // namespace bde

#else
namespace bde {
    class BindingInfo;
} // namespace bde
#endif
