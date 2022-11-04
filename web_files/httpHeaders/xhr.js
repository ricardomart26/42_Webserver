const getBtn = document.getElementById('get-btn');
const postBtn = document.getElementById('post-btn');

const sendHttpRequest = (method, url, data) => {
	const promise = new Promise ((resolve, reject) => {

		const xhr = new XMLHttpRequest();

		// Prepara o http para ser enviado
		xhr.open(method, url);

		// Faz o parsing automaticamente do pedido de json para js
		xhr.responseType = 'json';
		xhr.setRequestHeader('Content-type', 'application/json');
		// xhr.setRequestHeader('', 'application/json');

		xhr.onload = () => {
			if (xhr.status >= 400) {
				reject(xhr.response);
			}
			resolve(xhr.response)
		};

		xhr.onerror = () => {
			reject('Something went wrong');
		}

		xhr.send(JSON.stringify(data));
	});
	return promise;
}

const getData = () => 
{
	sendHttpRequest('GET', "https://regres.in/api/users").then(responseData => {
		console.log(responseData);
	});
};

const sendData = () => 
{
	sendHttpRequest('POST', "https://regres.in/api/register", {
		email: "test@test.com",
		password: 'tested'
	}).then(responseData => {
		console.log(responseData);
	}).catch(err => {
		console.log(err);
	});
};

getBtn.addEventListener('click', getData);
postBtn.addEventListener('click', sendData);

