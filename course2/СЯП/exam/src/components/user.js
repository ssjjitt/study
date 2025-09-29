import React, { useState } from "react";

function UserList() {
  const [users, setUsers] = useState([
    { id: 1, firstName: "John", lastName: "Doe", age: 25 },
    { id: 2, firstName: "Jane", lastName: "Smith", age: 30 },
    { id: 3, firstName: "Mike", lastName: "Johnson", age: 35 },
  ]);
  return (
    <div>
      <h1>User List</h1>
      {users.map((user) => (
        <User key={user.id} user={user} />
      ))}
    </div>
  );
}

function User({ user }) {
  return (
    <div>
      <p>
        Name: {user.firstName} {user.lastName}
      </p>
      <p>Age: {user.age}</p>
    </div>
  );
}

export default UserList;
