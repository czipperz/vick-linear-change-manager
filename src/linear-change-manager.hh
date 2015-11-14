#include "../../../src/contents.hh"

namespace vick {
namespace linear_change_manager {

/*!
 * \brief Undoes the change on top of the stack, or pops off another
 * if called again
 *
 * \code{.cpp}
 * ----------
 * | ------ |
 * | before |
 * | after  |
 * | ------ |
 * ----------
 * \endcode
 */
boost::optional<std::shared_ptr<change> >
undo_change(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Redoes the change on top of the stack, or climbs back on it 
 * Deletes anything after current
 *
 * \code{.cpp}
 * ----------
 * | ------ |
 * | after  |
 * | before |
 * | ------ |
 * ----------
 * \endcode
 */
boost::optional<std::shared_ptr<change> >
redo_change(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Reapplies the current change on the current position
 * Deletes anything after current
 *
 * \code{.cpp}
 * -----------------------
 * | current (reapplied) |
 * | current             |
 * | ------------------- |
 * -----------------------
 * \endcode
 */
boost::optional<std::shared_ptr<change> >
reapply_change(contents&, boost::optional<int> = 0);

}
}
