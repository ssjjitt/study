const log = (msg) => {
  document.getElementById("log").textContent += msg + "\n";
};

const connection = new signalR.HubConnectionBuilder()
  .withUrl("https://localhost:7037/calculatorHub")
  .withAutomaticReconnect()
  .build();

connection.serverTimeoutInMilliseconds = 30000;
connection.keepAliveIntervalInMilliseconds = 10000;

async function start() {
  try {
    await connection.start();
    log("Connected");
  } catch (err) {
    log("Connection error: " + err);
    setTimeout(start, 2000);
  }
}

connection.onclose(() => {
    log("Disconnected. Trying to reconnect...");
    start();
});

start();

async function invoke(name, ...args) {
  try {
    const result = await connection.invoke(name, ...args);
    log(`${name}(${args.join(", ")}) = ${result}`);
  } catch (err) {
    log(`${name}(${args.join(", ")}) — ERROR: ${err?.message || err}`);
  }
}

document.getElementById("btnSum").addEventListener("click", () => {
  const x = parseFloat(document.getElementById("x").value);
  const y = parseFloat(document.getElementById("y").value);
  invoke("SUM", x, y);
});

document.getElementById("btnSub").addEventListener("click", () => {
  const x = parseFloat(document.getElementById("x").value);
  const y = parseFloat(document.getElementById("y").value);
  invoke("SUB", x, y);
});

document.getElementById("btnMul").addEventListener("click", () => {
  const x = parseFloat(document.getElementById("x").value);
  const y = parseFloat(document.getElementById("y").value);
  invoke("MUL", x, y);
});

document.getElementById("btnDiv").addEventListener("click", () => {
  const x = parseFloat(document.getElementById("x").value);
  const y = parseFloat(document.getElementById("y").value);
  invoke("DIV", x, y);
});

document.getElementById("btnFact").addEventListener("click", () => {
  const n = parseInt(document.getElementById("n").value, 10);
  invoke("FACT", n);
});
