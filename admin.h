#ifndef ADMIN_H
#define ADMIN_H

#include "TreeRak.h" // Agar TreeNode dikenali
#include "Queue.h"

void menuAdmin(TreeNode* rootSupermarket);
void registerAdmin();
int loginAdmin();
void adminMenu(TreeNode* rootSupermarket);
void saveAdminReport(Queue* q, const char* filename);

#endif
