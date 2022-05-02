import numpy as np


def make_txt_matrix(square_dim: int, num_range: np.double, matrix_name: str) -> np.void:
    M = np.around(np.random.uniform(low=-num_range, high=num_range, size=(square_dim, square_dim)), decimals=2)

    mat = np.matrix(M)

    with open(matrix_name,'wb') as f:
        f.write(f"{square_dim} {square_dim}\n".encode())
        for line in mat:
            np.savetxt(f, line, fmt='%.2f')


def main():
    # config
    square_dim = 500
    random_range = 20
    for i in range(5):
        current_dim = (square_dim + 100*i)
        make_txt_matrix(square_dim = current_dim, num_range=random_range, matrix_name=f"m1_{current_dim}.txt")
        make_txt_matrix(square_dim = current_dim, num_range=random_range, matrix_name=f"m2_{current_dim}.txt")
        
main()