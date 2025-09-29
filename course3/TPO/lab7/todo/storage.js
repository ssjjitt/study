const fs = require('fs');
const todoFile = 'todo_list.json';

function loadTasks() {
    if (fs.existsSync(todoFile)) {
        const data = fs.readFileSync(todoFile);
        return JSON.parse(data);
    }
    return [];
}

function saveTasks(tasks) {
    fs.writeFileSync(todoFile, JSON.stringify(tasks, null, 4));
}

module.exports = { loadTasks, saveTasks };