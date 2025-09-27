function faz_uma_repeticao_while(X, n) 
{ 
	let i=0; 
	let result=1; 
	while(i<n) 
	{ 
		result=result * X; 
		i++; 
	} 
	return result; 
} 	

let s;

s = faz_uma_repeticao_while(2,4); 

console.log("Resultado = " + s); 
