// function addTask(description) {
//     const { loadTasks, saveTasks } = require('./storage');
//     const tasks = loadTasks();
//     tasks.push({ id: tasks.length + 1, task: description, done: false });
//     saveTasks(tasks);
// }

// function listTasks() {
//     const { loadTasks } = require('./storage');
//     return loadTasks();
// }

// function updateTask(taskId, newDescription) {
//     const { loadTasks, saveTasks } = require('./storage');
//     const tasks = loadTasks();
//     const task = tasks.find(t => t.id === taskId);
//     if (task) {
//         task.task = newDescription;
//         saveTasks(tasks);
//         return true;
//     }
//     return false;
// }

// function deleteTask(taskId) {
//     const { loadTasks, saveTasks } = require('./storage');
//     let tasks = loadTasks();
//     const newTasks = tasks.filter(t => t.id !== taskId);
//     if (newTasks.length !== tasks.length) {
//         saveTasks(newTasks);
//         return true;
//     }
//     return false;
// }

// function markDone(taskId) {
//     const { loadTasks, saveTasks } = require('./storage');
//     const tasks = loadTasks();
//     const task = tasks.find(t => t.id === taskId);
//     if (task) {
//         task.done = true;
//         saveTasks(tasks);
//         return true;
//     }
//     return false;
// }

// module.exports = { addTask, listTasks, updateTask, deleteTask, markDone };
