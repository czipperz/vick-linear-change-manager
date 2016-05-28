/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "contents.hh"

namespace vick {
namespace linear_change_manager {

/*!
 * \file linear-change-manager.hh
 * \brief Linearly manages the changes in the contents buffer.
 *
 * If a change is added while we have undone some, the undone ones are
 * discarded.
 */

/*!
 * \brief Adds the change given to the private vector, possibly
 * deleting some changes
 *
 * ----------
 * | change |
 * | ------ |
 * ----------
 *
 * \param change The string to be put at the end of the vector of
 * changes.
 */
void push_back_change(contents& contents,
                      std::shared_ptr<change> change);

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
