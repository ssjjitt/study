const axios = require('axios');
const util = require('util');

const options = {
    method: 'GET',
    url: 'https://api.restful-api.dev/objects/',
    params: {
        id: "",
    },
    headers: {
        'Content-Type': 'application/json',
    }
};

test('GET результаты с невалидными данными', async () => {
    const response = await axios.request(options);
    expect(response.status).toBe(200);
    //console.log(util.inspect(response.data, { depth: null, colors: true }));
});