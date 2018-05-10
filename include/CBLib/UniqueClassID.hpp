#ifndef CB_UNIQUECLASSID_HPP
#define CB_UNIQUECLASSID_HPP

#include <iostream>

namespace cb
{

/*
// For receiving a unique id for classes.
*/
namespace uniqueClassID
{

/*
// Calling:
// -> cb::UniqueClassID::getUniqueId<YOURCLASS>();
// returns a unsigned integer with an unique id for classes
*/
template <class T>
static std::size_t getUniqueId()
{
    // Unique id counter as the class attribute.
    // Will only be called once for every new class 'template-parameter'
    static std::size_t id = internal::uid++;
    return id;
}

namespace internal
{
    static std::size_t uid;
} // namespace internal

} // namespace uniqueClassID

} // namespace cb

#endif