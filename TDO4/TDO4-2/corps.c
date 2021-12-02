void InvShiftRows2()
{
	unsigned char temp;

	temp = state[0][3] & 1;
	state[0][3] >>= 1;
	state[0][3] ^= ((state[0][2]) << 7);
	state[0][2] >>= 1;
	state[0][2] ^= ((state[0][1]) << 7);
	state[0][1] >>= 1;
	state[0][1] ^= ((state[0][0]) << 7);
	state[0][0] >>= 1;
	state[0][0] ^= (temp << 7);

	temp = state[1][3] & 3;
	state[1][3] >>= 2;
	state[1][3] ^= ((state[1][2]) << 6);
	state[1][2] >>= 2;
	state[1][2] ^= ((state[1][1]) << 6);
	state[1][1] >>= 2;
	state[1][1] ^= ((state[1][0]) << 6);
	state[1][0] >>= 2;
	state[1][0] ^= (temp << 6);

	temp = state[2][3] & 7;
	state[2][3] >>= 3;
	state[2][3] ^= ((state[2][2]) << 5);
	state[2][2] >>= 3;
	state[2][2] ^= ((state[2][1]) << 5);
	state[2][1] >>= 3;
	state[2][1] ^= ((state[2][0]) << 5);
	state[2][0] >>= 3;
	state[2][0] ^= (temp << 5);

	temp = state[3][3] & 15;
	state[3][3] >>= 4;
	state[3][3] ^= ((state[3][2]) << 4);
	state[3][2] >>= 4;
	state[3][2] ^= ((state[3][1]) << 4);
	state[3][1] >>= 4;
	state[3][1] ^= ((state[3][0]) << 4);
	state[3][0] >>= 4;
	state[3][0] ^= (temp << 4);
}

void InvCipher() /*Fonction de Déchiffrement*/
{
	int i, j, round = 0;

	/*Copie du texte chiffré (128 bits) dans la matrice 4x4 state, attention la copie est faite sur les colonnes*/
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			state[j][i] = in[i * 4 + j];
		}
	}

	AddRoundKey(Nr);
	InvShiftRows2();
	InvSubBytes();

	for (round = Nr - 1; round > 0; round--)
	{
		AddRoundKey(round);
		InvMixColumns();
		InvShiftRows2();
		InvSubBytes();
	}

	AddRoundKey(0);

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			out[i * 4 + j] = state[j][i];
		}
	}
}

void Cipher_Mode_1(FILE *FIC_IN, FILE *FIC_OUT)
{
	int i, k, caract, continuer = 1;

	while (continuer == 1)
	{
		k = 0;
		while (k < 16 && (caract = fgetc(FIC_IN)) != EOF)
		{
			in[k] = (unsigned char)caract;
			k++;
		}

		if (k == 0 && caract == EOF)
		{
			break;
		}
		else if (k > 0 && caract == EOF)
		{
			while (k < 16)
			{
				in[k] = 0;
				k++;
			}
			continuer = 0;
		}

		Cipher();

		for (i = 0; i < Nb * 4; i++)
		{
			fputc(out[i], FIC_OUT);
		}
	}
}

void Cipher_Mode_2(FILE *FIC_IN, FILE *FIC_OUT)
{
	int i, k, caract, continuer = 1;
	unsigned char VI[16] = {0x87, 0x51, 0x1B, 0xC9, 0x95, 0xFB, 0x13, 0xA4, 0x0B, 0xE3, 0x4E, 0xC4, 0x33, 0xD5, 0x3D, 0xB3};
	for (i = 0; i < 16; i++)
	{
		out[i] = VI[i];
	}
	while (continuer == 1)
	{
		k = 0;
		while (k < 16 && (caract = fgetc(FIC_IN)) != EOF)
		{
			in[k] = (unsigned char)caract;
			k++;
		}

		if (k == 0 && caract == EOF)
		{
			break;
		}
		else if (k > 0 && caract == EOF)
		{
			while (k < 16)
			{
				in[k] = 0;
				k++;
			}
			continuer = 0;
		}

		for (i = 0; i < 16; i++)
		{
			in[i] = in[i] ^ out[i];
		}

		Cipher();

		for (i = 0; i < Nb * 4; i++)
		{
			fputc(out[i], FIC_OUT);
		}
	}
}