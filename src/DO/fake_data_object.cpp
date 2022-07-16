#include "DO/fake_data_object.h"

int rvm::FakeDataObject::set(const uint8_t &id, const uint32_t &size, const uint32_t &accessTime)
{
    if (size == 0)
    {
        throw std::string("Error DO_" + std::to_string(id) + ": in set(), size == 0");
    }

    this->id = id;
    this->size = size;
    this->accessTime = accessTime;

    /* Allocate mem */
    data = new uint8_t[size];

    /* Filling zeros */
    for (size_t i = 0; i < size; i++)
    {
        data[i] = 0;
    }

    /* Set status */
    status.id = id;

    //! need to confirm to CU?
    // cu->sendStatusFromDataObject(status);
    return 0;
}