#include "polynom.h"

#define READ_COUNT 1

poly_data_t *create_polynom_data(const int coef, const int power)
{
    poly_data_t *data = malloc(sizeof(struct polynom_data));

    if (data != NULL)
    {
        data->coef = coef;
        data->power = power;
    }

    return data;
}

int cmp_poly_data(const void *a, const void *b)
{
    return ((poly_data_t *)b)->power - ((poly_data_t *)a)->power;
}

list_t sort_polynom(list_t polynom)
{
    return sort(polynom, cmp_poly_data);
}

void add_poly_data(poly_data_t *a, poly_data_t *b)
{
    a->coef = a->coef + b->coef;
}

list_t sum_polynoms(list_t *polynom_a, list_t *polynom_b)
{
    list_t sum_polynom = NULL, curr_a, new_a_elem;
    poly_data_t *curr_data_b;
    int was_summed;
    
    while (polynom_b != NULL)
    {
        curr_data_b = (poly_data_t *) pop_front(polynom_b);

        if (curr_data_b == NULL)
            break;

        curr_a = *polynom_a;
        was_summed = 0;

        while ((curr_a != NULL) && (!was_summed))
        {
            if (cmp_poly_data(curr_a->data, curr_data_b) == 0)
            {
                ((poly_data_t *)curr_a->data)->coef += curr_data_b->coef;
                free_poly_data(curr_data_b);
                was_summed = 1;
            }
            else
                curr_a = curr_a->next;
        }
        
        if (!was_summed)
        {
            new_a_elem = alloc_elem(curr_data_b);

            if (new_a_elem == NULL)
            {
                free_polynom(polynom_a);
                free_polynom(polynom_b);
                return NULL;
            }

            *polynom_a = insert_elem_back(*polynom_a, new_a_elem);
        }
    }

    list_t next;
    curr_a = *polynom_a;

    while (curr_a != NULL)
    {
        next = curr_a->next;

        if (((poly_data_t *)curr_a->data)->coef != 0)
            sorted_insert(&sum_polynom, curr_a, cmp_poly_data);
        else
            free_elem(curr_a, free_poly_data);
    
        curr_a = next;
    }

    return sum_polynom;
}

void free_poly_data(void *data)
{
    free((poly_data_t *) data);
}

int get_arg_polynom_data(poly_data_t **data)
{
    int coef, power;

    if (scanf("%d", &coef) != READ_COUNT)
        return ERR_DATA;

    char symb = getc(stdin);

    /* printf("Symb: '%c'\n", symb); */

    if (symb != '\n')
    {
        if (scanf("%d", &power) != READ_COUNT)
            return ERR_DATA;
    }
    else
        power = -1;

    *data = create_polynom_data(coef, power);

    if (*data == NULL)
        return ERR_MEM;

    return EXIT_SUCCESS;
}

int get_polynom_data(poly_data_t **data)
{
    int coef, power;

    if (scanf("%d", &coef) != READ_COUNT)
        return ERR_DATA;

    if (scanf("%d", &power) != READ_COUNT)
        return ERR_DATA;

    *data = create_polynom_data(coef, power);

    if (*data == NULL)
        return ERR_MEM;

    if (fgetc(stdin) == '\n')
        return END_CODE;
    
    return EXIT_SUCCESS;
}

int input_polynom(list_t *polynom)
{
    int rc = EXIT_SUCCESS;
    poly_data_t *curr_data = (void *) 0xDEADBEEF;
    list_t curr_elem = NULL;

    *polynom = NULL;

    while (curr_data != NULL)
    {
        rc = get_polynom_data(&curr_data);

        if ((rc) && (rc != END_CODE))
        {
            free_polynom(polynom);
            return rc;
        }

        curr_elem = alloc_elem(curr_data);

        if (curr_elem == NULL)
        {
            free_polynom(polynom);
            return ERR_MEM;
        }

        *polynom = insert_elem_back(*polynom, curr_elem);

        if (rc == END_CODE)
            curr_data = NULL;
    }

    return EXIT_SUCCESS;
}

int input_arg_polynom(list_t *polynom, int *const arg)
{
    int rc = EXIT_SUCCESS;
    poly_data_t *curr_data = (void *) 0xDEADBEEF;
    list_t curr_elem = NULL;
    size_t count = 0;

    *polynom = NULL;

    while (curr_data != NULL)
    {
        rc = get_arg_polynom_data(&curr_data);

        if (rc)
        {
            free_polynom(polynom);
            return rc;
        }

        if (curr_data->power == -1)
        {
            *arg = curr_data->coef;
            free(curr_data);
            curr_data = NULL;
            
            if (count == 0)
                return ERR_DATA;
        }
        else
        {
            curr_elem = alloc_elem(curr_data);

            if (curr_elem == NULL)
            {
                free_polynom(polynom);
                return ERR_MEM;
            }

            *polynom = insert_elem_back(*polynom, curr_elem);
            count++;
        }
    }

    return EXIT_SUCCESS;
}

void print_poly_data(void *data)
{
    poly_data_t *poly_data = (poly_data_t *) data;

    printf("%d %d ", poly_data->coef, poly_data->power);
}

void print_polynom(list_t polynom)
{
    print_list(polynom, print_poly_data);
}

void free_polynom(list_t *polynom)
{
    free_list(*polynom, free_poly_data);
}

int calc_polynom(list_t polynom, const int arg)
{
    list_t curr = polynom;
    poly_data_t *curr_data = NULL;
    int res = 0;
    
    while (curr != NULL)
    {
        curr_data = (poly_data_t *) curr->data;
        res = res + curr_data->coef * (int) pow(arg, curr_data->power);
        curr = curr->next;
    }

    return res;
}

list_t get_ddx_polynom(list_t polynom)
{
    list_t new_polynom = NULL, curr = polynom, next, new_elem = NULL;
    int new_coef, new_power;
    poly_data_t *new_data = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        
        if (((poly_data_t *)curr->data)->power == 0)
            break;
        
        new_power = ((poly_data_t *)curr->data)->power;
        new_coef = ((poly_data_t *)curr->data)->coef * (new_power--);

        new_data = create_polynom_data(new_coef, new_power);

        if (new_data == NULL)
        {
            free_polynom(&new_polynom);
            return NULL;
        }
        
        new_elem = alloc_elem(new_data);

        if (new_elem == NULL)
        {
            free_polynom(&new_polynom);
            return NULL;
        }

        new_polynom = insert_elem_back(new_polynom, new_elem);

        curr = next;
    }

    return new_polynom; 
}

int is_even_poly_data(void *data)
{
    if (((poly_data_t *)data)->power % 2 == 0)
        return TRUE;

    return FALSE;
}

void get_odd_even_poly(list_t polynom, list_t *even, list_t *odd)
{
    list_t curr = polynom, next;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = NULL;

        if (is_even_poly_data(curr->data))
            *even = insert_elem_back(*even, curr);
        else
            *odd = insert_elem_back(*odd, curr);

        curr = next;
    }
}
