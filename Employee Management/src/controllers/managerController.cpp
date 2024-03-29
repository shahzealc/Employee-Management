#include "../../include/controllers/managerController.h"

using logs::Log;

bool ManagerController::insertManagerController(Manager& manager) {

    std::string insertQueryManager = "INSERT INTO Manager(id, management_experience , project_title) VALUES ("
        + std::to_string(manager.getId()) + ","
        + std::to_string(manager.getManagementExperience()) + ",'"
        + manager.getProjectTitle() + "');";

    auto s1 = std::make_unique<Salary>();

    if (Database::getInstance().executeQuery(insertQueryManager) && s1->insertSalaryById(manager.getId())) {
        std::cout << "\033[32mInserted Manager Successfully ! \033[0m\n\n";
        Log::getInstance().Info("Manager Inserted for id : ", manager.getId());
        return true;
    }
    else {
        std::cout << Database::getInstance().getError() << "\n\n";
        return false;
    }

}

bool ManagerController::deleteManagerController(Manager& manager, std::string attribute) {
    std::string deleteQuery{};
    if (attribute == "id") {
        deleteQuery = "DELETE FROM Manager WHERE id = " + std::to_string(manager.getId());
    }

    if (!Database::getInstance().executeQuery(deleteQuery)) {
        std::cout << Database::getInstance().getError() << "\n";
        return false;
    }

    int changes = sqlite3_changes(Database::getInstance().db);

    std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
    if (changes != 0) {
        std::cout << "\033[32mManager Deleted Successfully ! \033[0m\n\n";
        Log::getInstance().Info("Manager Deleted for id : ", manager.getId());
        return true;
    }

    return false;
}

bool ManagerController::updateManagerController(Manager& manager, std::string attribute) {
    std::string updateQuery = "UPDATE Manager SET ";
    if (attribute == "management_experience") {
        updateQuery += " management_experience = '" + std::to_string(manager.getManagementExperience()) + "'";
    }
    else if (attribute == "project_title") {
        updateQuery += " project_title= '" + manager.getProjectTitle() + "'";
    }

    updateQuery += " WHERE id = " + std::to_string(manager.getId()) + ";";

    if (Database::getInstance().executeQuery(updateQuery)) {
        int changes = sqlite3_changes(Database::getInstance().db);
        std::cout << "\033[32m" << changes << " row affected \033[0m\n\n";
        if (changes != 0) {
            std::cout << "\033[32mManager Updated Successfully ! \033[0m\n\n";
            Log::getInstance().Info("Manager Updated for id : ", manager.getId());
            return true;
        }
    }
    else {
        std::cout << Database::getInstance().getError() << "\n";
        return false;
    }
}

bool ManagerController::viewManagerController(std::string selectQuery) {
    if (!Database::getInstance().executeQueryCallback(selectQuery)) {
        std::cout << Database::getInstance().getError() << std::endl;
        return false;
    }
    else {
        Log::getInstance().Info(selectQuery, " : Executed.");
        return true;
    }
}