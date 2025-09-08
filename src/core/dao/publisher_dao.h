#ifndef PUBLISHER_DAO_H
#define PUBLISHER_DAO_H

#include "core/db/db.h"
#include "core/models/enum.h"

dao_status publisher_dao_create(DAOContext *ctx, const char *company_name, int *out_new_id);

#endif //PUBLISHER_DAO_H
