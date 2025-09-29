// Fetch JSON and display it in the browser
fetch('/json/json.json')
.then(response => response.json()) // Parse JSON response
.then(data => {
    document.getElementById('json-content-display').textContent = JSON.stringify(data, null, 2); // Display formatted JSON
})
.catch(error => console.error('Error fetching JSON:', error));

// Fetch XML and display it in the browser
fetch('/xml/xml.xml')
.then(response => response.text()) // Get XML as text
.then(data => {
    document.getElementById('xml-content-display').textContent = data; // Display XML as text
})
.catch(error => console.error('Error fetching XML:', error));