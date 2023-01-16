#include "Logger.h"

void Logger::checkAction(long systime) {
    // s. Logger.h
    action(systime);

}


String Logger::getID() {
    return nameID;
}
