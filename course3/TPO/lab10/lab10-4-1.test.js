const request = require('supertest');
const express = require('express');
const app = require('./index'); // Предполагается, что сервер экспортируется

let token;

describe('Access Control API', () => {
  it('Login as user1 and get token', async () => {
    const res = await request(app)
      .post('/login')
      .send({ username: 'user1' });
    expect(res.statusCode).toBe(200);
    expect(res.body.token).toBeDefined();
    token = res.body.token;
  });

  it('Access own data (user1 -> user1)', async () => {
    const res = await request(app)
      .get('/users/1')
      .set('Authorization', `Bearer ${token}`);
    expect(res.statusCode).toBe(200);
    expect(res.body.username).toBe('user1');
  });

  it('Access other user data (user1 -> user2)', async () => {
    const res = await request(app)
      .get('/users/2')
      .set('Authorization', `Bearer ${token}`);
    expect(res.statusCode).toBe(403);
  });

  it('Access without token', async () => {
    const res = await request(app).get('/users/1');
    expect(res.statusCode).toBe(403);
  });
});
