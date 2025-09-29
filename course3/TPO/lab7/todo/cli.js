const { Command } = require('commander');
const { addTask, listTasks, updateTask, deleteTask, markDone } = require('./tasks');

const program = new Command();

program
    .command('add <description>')
    .description('Add a new task')
    .action(addTask);

program
    .command('list')
    .description('List all tasks')
    .action(() => {
        const tasks = listTasks();
        tasks.forEach(task => {
            const status = task.done ? '[✔]' : '[ ]';
            console.log(`${task.id}. ${status} ${task.task}`);
        });
    });

program
    .command('update <taskId> <newDescription>')
    .description('Update a task')
    .action(updateTask);

program
    .command('delete <taskId>')
    .description('Delete a task')
    .action(deleteTask);

program
    .command('done <taskId>')
    .description('Mark task as done')
    .action(markDone);

program.parse(process.argv);