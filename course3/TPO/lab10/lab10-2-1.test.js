const axios = require('axios');

const baseURL = 'https://api.restful-api.dev/objects';

describe('CRUD Testing on /objects API', () => {
    let objectId;

    test('CREATE: добавить объект (POST)', async () => {
        const res = await axios.post(baseURL, {
            name: "Apple MacBook Pro 16",
            data: {
                year: 2019,
                price: 1849.99,
                "CPU model": "Intel Core i9",
                "Hard disk size": "1 TB"
            }
        });

        expect(res.status).toBe(200);
        expect(res.data).toHaveProperty('id');
        expect(res.data.name).toBe("Apple MacBook Pro 16");
        objectId = res.data.id;
    });

    test('READ: получить объект по ID (GET)', async () => {
        const res = await axios.get(`${baseURL}/${objectId}`);
        expect(res.status).toBe(200);
        expect(res.data.id).toBe(objectId);
        expect(res.data.name).toBe("Apple MacBook Pro 16");
    });

    test('UPDATE: обновить объект (PUT)', async () => {
        const res = await axios.put(`${baseURL}/${objectId}`, {
            name: "MacBook Pro Updated",
            data: {
                year: 2020,
                price: 1999.99,
                "CPU model": "Intel Core i7",
                "Hard disk size": "2 TB"
            }
        });

        expect(res.status).toBe(200);
        expect(res.data.name).toBe("MacBook Pro Updated");
        expect(res.data.data.price).toBe(1999.99);
    });

    test('DELETE: удалить объект (DELETE)', async () => {
        const res = await axios.delete(`${baseURL}/${objectId}`);
        expect(res.status).toBe(200);
        expect(res.data.message).toMatch(/has been deleted/i);
    });

    test('GET после DELETE: должен вернуть ошибку или не найти объект', async () => {
        try {
            await axios.get(`${baseURL}/${objectId}`);
        } catch (err) {
            expect(err.response.status).toBe(404);
        }
    });
});
