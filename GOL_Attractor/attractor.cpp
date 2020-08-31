#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>

using namespace std;

int screenWidth = 4;
int screenHeight = 4;

void fill_array(int *array1, int *array2);
void print_matrix(int *array);
long int matrix_to_dec(int *array);
void game_ov_life(int *m_output, int *m_state);

int main()
{
	int *m_output;
	int *m_state;
	int i, j, counter;
	int combination, index;
	long int m_state_val, m_output_val;
	bool first_time, continue_life;
	long int n_values = pow(2, screenWidth * screenHeight);
	bool values[n_values];
	ofstream save_writer;

	m_output = new int[screenWidth * screenHeight];
	m_state = new int[screenWidth * screenHeight];

	memset(values, false, n_values * sizeof(bool));
	memset(m_output, 0, screenWidth * screenHeight * sizeof(int));
	memset(m_state, 0, screenWidth * screenHeight * sizeof(int));

	save_writer.open("data.dat", ios_base::out | ios_base::trunc);
	if(!save_writer)
	{
		cout << "Error: Cannot open 'strings' file" << endl;
		exit(EXIT_FAILURE);
	}
	
	// GENERAMOS CSV
	for(combination = 0; combination < pow(2, screenWidth * screenHeight); combination++)
	{
		first_time = true;
		continue_life = true;
		counter = 0;
		while(continue_life)
		{
			// ARRRANCAMOS LIFE CON LA CADENA CORRESPONDIENTE
			if(first_time)
			{
				index = 0;
				for(i = (int) pow(2, (screenWidth * screenHeight) - 1); i > 0; i = i >> 1)
				{
					if(i & combination)
						m_state[index++] = 1;
					else
						m_state[index++] = 0;
				}
				first_time = false;
			}
			
			// VACIAMOS M_STATE EN M_OUTPUT
			fill_array(m_state, m_output);

			// TRANSFORMAMOS M_OUTPUT EN DECIMAL
			m_output_val = matrix_to_dec(m_output);
			
			// ESCRIBÍMOS EL VALOR EN UN .CSV
			save_writer << (m_output_val + 1) << ",";
			counter++;

			// APLICAMOS ALGORITMO LIFE
			game_ov_life(m_output, m_state);

			// ESTA BANDERA DECIDE SI SE SIGUEN EJECUTANDO LOS PASOS DE LIFE
			continue_life = true;

			// TRANSFORMAMOS M_STATE A VALOR DECIMAL
			m_state_val = matrix_to_dec(m_state);

			// SI YA HABÍAMOS OBTENIDO ESE VALOR DEJAMOS DE ITERAR
			if(values[m_state_val])
				continue_life = false;

			// MARCAMOS EL VALOR COMO YA CALCULADO
			values[m_state_val] = true;

			// HACEMOS LA BUSQUEDA DE POSIBLES CONDICIONES DE PARO
			if(continue_life)
			{
				// BUSCANDO SI YA ESTA MUERTO EL SISTEMA ES DECIR HAY PUROS CEROS
				if(m_state_val == 0)
					continue_life = false;

				// SI NO HA MUERTO EL SISTEMA CHECAMOS SI YA SE REPITIÓ EL ESTADO
				if(continue_life)
				{
					if(m_output_val == m_state_val)
						continue_life = false;
				}
			}
			
			// SI YA SE ACABA EL SISTEMA GUARDAMOS EL ÚLTIMO DATO
			if(!continue_life)
			{
				save_writer << (m_state_val + 1);
				counter++;
			} 
		}

		// if(counter < 3)
		// {
		// 	save_writer << ",1"; 
		// }
		save_writer << endl;
	}	
	
	save_writer.close();

	return 0;
}

long int matrix_to_dec(int *array)
{
	long int dec_value = 0;
	int exponent = (screenWidth * screenHeight) - 1;
	for(int i = 0; i < screenWidth * screenHeight; i++)
	{
		if(array[i])
			dec_value += pow(2, exponent);

		exponent--;
	}

	return dec_value;
}

void game_ov_life(int *m_output, int *m_state)
{
	int nNeighbours;

	auto cell = [&](int x, int y)
	{
		return m_output[y * screenWidth + x];
	};

	for(int x = 0; x < screenWidth; x++)
	{
		for(int y = 0; y < screenHeight; y++)
		{
			nNeighbours = 0;
			for(int i = -1; i < 2; i++)
				for(int j = -1; j < 2; j++)
					nNeighbours += cell((x + i + screenWidth) % screenWidth, (y + j + screenHeight) % screenHeight);

			nNeighbours -= cell(x, y);
			
			if(cell(x, y) == 1)
				m_state[y * screenWidth + x] = nNeighbours == 7; //|| nNeighbours == 3;
			else
				m_state[y * screenWidth + x] = nNeighbours == 2;
		}
	}
}

void print_matrix(int *array)
{
	printf("MATRIX\n");
	for(int y = 0; y < screenWidth; y++)
	{
		for(int x = 0; x < screenHeight; x++)
			printf("%d ", array[y * screenWidth + x]);
		printf("\n");
	}
}

void fill_array(int *array1, int *array2)
{
	for (int i = 0; i < screenWidth * screenHeight; i++)
		array2[i] = array1[i];		
}
