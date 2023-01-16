#include "Logger.h"

void Logger::checkAction(long systime) {
    action(systime);

}


String Logger::getID() {
    return nameID;
}
