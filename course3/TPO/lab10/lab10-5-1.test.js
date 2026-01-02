const request = require('supertest');
const express = require('express');
const app = require('./index'); 

describe('Validation tests', () => {
  it('Too long username', async () => {
    const res = await request(app)
      .post('/users')
      .send({ username: 'x'.repeat(100), age: 25 });

    expect(res.statusCode).toBe(404);
  });

  it('Age out of range (negative)', async () => {
    const res = await request(app)
      .post('/users')
      .send({ username: 'validUser', age: -5 });

    expect(res.statusCode).toBe(404);
  });

  it('Missing required field (username)', async () => {
    const res = await request(app)
      .post('/users')
      .send({ age: 30 });

    expect(res.statusCode).toBe(404);
  });
});
