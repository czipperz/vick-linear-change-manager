/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>

#include "contents.hh"
#include "show_message.hh"
#include "../lib.hh"

namespace vick {
namespace linear_change_manager {

void push_back_change(contents& contents,
                      std::shared_ptr<change> change) {
    if (contents.changes_i == 0)
        contents.changes.clear();
    else if (contents.changes.size() > contents.changes_i)
        contents.changes.erase(contents.changes.begin() +
                                   contents.changes_i,
                               contents.changes.end());
    contents.changes.push_back(change);
    contents.changes_i = contents.changes.size();
}

boost::optional<std::shared_ptr<change> >
undo_change(contents& contents, boost::optional<int>) {
    if (contents.changes.empty() or contents.changes_i == 0) {
        show_message("No changes to undo");
        return boost::none;
    }
    contents.changes[--contents.changes_i]->undo(contents);
    return boost::none;
}

boost::optional<std::shared_ptr<change> >
redo_change(contents& contents, boost::optional<int>) {
    if (contents.changes.empty() or
        contents.changes_i >= contents.changes.size()) {
        show_message("No changes to redo");
        return boost::none;
    }
    contents.changes[contents.changes_i++]->redo(contents);
    return boost::none;
}

boost::optional<std::shared_ptr<change> >
reapply_change(contents& contents, boost::optional<int>) {
    if (contents.changes.empty()) {
        show_message("No changes to reapply");
        return boost::none;
    }
    return contents.changes.back()->regenerate_and_apply(contents);
}
}
}
