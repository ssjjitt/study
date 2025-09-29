const axios = require('axios');

const baseURL = 'https://api.restful-api.dev/objects';

describe('CRUD Testing on /objects API', () => {
    test('Ошибка: POST с пустым телом', async () => {
        try {
            await axios.post(baseURL, {});
        } catch (err) {
            expect(err.response.status).toBe(400);
            expect(err.response.data.message || err.response.data.error).toBeDefined();
        }
    });

    test('Ошибка: POST с невалидным форматом данных (строка вместо числа)', async () => {
        try {
            await axios.post(baseURL, {
                name: "Invalid Device",
                data: {
                    year: "не число", 
                    price: "дорого",
                    "CPU model": 12345,
                    "Hard disk size": true
                }
            });
        } catch (err) {
            expect(err.response.status).toBe(400);
            expect(err.response.data.message || err.response.data.error).toBeDefined();
        }
    });

    test('Ошибка: запрос на несуществующую конечную точку', async () => {
        try {
            await axios.get('https://api.restful-api.dev/wrong-endpoint');
        } catch (err) {
            expect(err.response.status).toBe(404);
            expect(err.response.data.message || err.response.data.error).toBeDefined();
        }
    });
});


