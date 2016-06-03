#include "bnr_base_locgic.h"
#include "mslotitem.h"

Bnr_base_locgic::Bnr_base_locgic(QObject *parentmslot,QObject *parent) :
    QObject(parent)
{
    this->parentmslot = parentmslot;
    initflag=false;
}
bool Bnr_base_locgic::init(){
    mslotitem *parent_item = (mslotitem *)parentmslot;
    initflag=true;

}
void Bnr_base_locgic::loop(){

}
