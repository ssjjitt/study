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
        'access-control-allow-credentials': 'true',
        'access-control-allow-origin': '*',
    }
};

test('GET результаты с headers', async () => {
    const response = await axios.request(options);
    expect(response.status).toBe(200);
    //console.log(util.inspect(response.data, { depth: null, colors: true }));
});

