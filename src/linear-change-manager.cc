#include <ncurses.h>

#include "../../../src/contents.hh"
#include "../../../src/show_message.hh"

namespace vick {
namespace linear_change_manager {

void contents::push_back(std::shared_ptr<change> change)
{
    if (changes_i == 0)
        changes.clear();
    else if (changes.size() > changes_i)
        changes.erase(changes.begin() + changes_i, changes.end());
    changes.push_back(change);
    changes_i = changes.size();
}

boost::optional<std::shared_ptr<change> > undo_change(contents& contents,
                                                      boost::optional<int>)
{
    if (contents.changes.size() == 0 || contents.changes_i == 0) {
        show_message("No changes to undo");
        return boost::none;
    }
    contents.changes[--contents.changes_i]->undo(contents);
    return boost::none;
}

boost::optional<std::shared_ptr<change> > redo_change(contents& contents,
                                                      boost::optional<int>)
{
    if (contents.changes.size() == 0 || contents.changes_i >= contents.changes.size()) {
        show_message("No changes to redo");
        return boost::none;
    }
    contents.changes[contents.changes_i++]->redo(contents);
    return boost::none;
}

boost::optional<std::shared_ptr<change> > reapply_change(contents& contents,
                                                         boost::optional<int>)
{
    if (contents.changes.size() == 0) {
        show_message("No changes to reapply");
        return boost::none;
    }
    contents.changes_i++;
    auto x = contents.changes.back()->regenerate(contents);
    x->redo(contents);
    return x;
}

}
}
