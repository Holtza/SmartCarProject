/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_CORE_REFLECTION_MESSAGE_H_
#define OPENDAVINCI_CORE_REFLECTION_MESSAGE_H_

#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/generated/odcore/data/reflection/AbstractField.h"

namespace odcore { namespace base { class Visitor; } }

namespace odcore {
    namespace reflection {

template <typename T> class Field;

        using namespace std;

        /**
         * This class is a generic Message representation.
         */
        class OPENDAVINCI_API Message : public odcore::base::Visitable {
            public:
                Message();

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                Message(const Message &obj);

                virtual ~Message();

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                Message& operator=(const Message &obj);

            public:
                virtual void accept(odcore::base::Visitor &v);

            private:
                /**
                 * This method retrieves the current value from the list of
                 * fields, visits the value, and updates it in the case that
                 * the Visitor might have altered the value.
                 *
                 * @param v Visitor.
                 * @param f Field to visit.
                 */
                template<typename T>
                void visitPrimitiveDataType(odcore::base::Visitor &v, std::shared_ptr<odcore::data::reflection::AbstractField> &f) {
                    // Read value.
                    T value = dynamic_cast<odcore::reflection::Field<T>*>(f.operator->())->getValue();
                    // Visit value.
                    v.visit(f->getLongFieldIdentifier(), f->getShortFieldIdentifier(),
                            f->getLongFieldName(), f->getShortFieldName(), value);
                    // Update value.
                    dynamic_cast<odcore::reflection::Field<T>*>(f.operator->())->setValue(value);
                }

            public:
                /**
                 * This method adds a field to this generic message representation.
                 *
                 * @param Field to be added.
                 */
                void addField(const std::shared_ptr<odcore::data::reflection::AbstractField> &f);

                /**
                 * This method tries to find a field using first the long identifier;
                 * if the field was not found, the short identifier is used.
                 *
                 * @param longIdentifier to find.
                 * @param shortIdentifier to find.
                 * @param found Flag modified by this method indicating if the field was found.
                 * @return field Be aware to always check 'found' whether the field was found.
                 */
                std::shared_ptr<odcore::data::reflection::AbstractField> getFieldByLongIdentifierOrShortIdentifier(const uint32_t &longIdentifier, const uint8_t &shortIdentifier, bool &found);

            private:
                /**
                 * This method tries to find a field using the long identifier.
                 *
                 * @param longIdentifier to find.
                 * @param found Flag modified by this method indicating if the field was found.
                 * @return field Be aware to always check 'found' whether the field was found.
                 */
                std::shared_ptr<odcore::data::reflection::AbstractField> getFieldByLongIdentifier(const uint32_t &longIdentifier, bool &found);

                /**
                 * This method tries to find a field using the short identifier.
                 *
                 * @param shortIdentifier to find.
                 * @param found Flag modified by this method indicating if the field was found.
                 * @return field Be aware to always check 'found' whether the field was found.
                 */
                std::shared_ptr<odcore::data::reflection::AbstractField> getFieldByShortIdentifier(const uint8_t &shortIdentifier, bool &found);

            private:
                vector<std::shared_ptr<odcore::data::reflection::AbstractField> > m_fields;
        };

    }
} // odcore::reflection

#endif /*OPENDAVINCI_CORE_REFLECTION_MESSAGE_H_*/
