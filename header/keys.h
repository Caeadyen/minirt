/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:30:18 by hrings            #+#    #+#             */
/*   Updated: 2022/10/29 13:30:43 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __linux__
#  define ESC 				65307
#  define NUM_PAD_0			65438
#  define NUM_PAD_1			65436
#  define NUM_PAD_2			65433
#  define NUM_PAD_3			65435
#  define NUM_PAD_4			65430
#  define NUM_PAD_5			65437
#  define NUM_PAD_6			65432
#  define NUM_PAD_7			65429
#  define NUM_PAD_8			65431
#  define NUM_PAD_9			65434
#  define NUM_PAD_PLUS		65451
#  define NUM_PAD_MINUS		65453
#  define NUM_PAD_DEL		65439
#  define NUM_PAD_MULTI		65450
#  define NUM_PAD_DEVIDE	65455
#  define A_KEY 			97
#  define S_KEY 			115
#  define D_KEY 			100
#  define W_KEY 			119
#  define Q_KEY 			113
#  define E_KEY 			101
# endif
# ifdef __APPLE__
#  define ESC 				53
#  define NUM_PAD_0			82
#  define NUM_PAD_1			83
#  define NUM_PAD_2			84
#  define NUM_PAD_3			85
#  define NUM_PAD_4			86
#  define NUM_PAD_5			87
#  define NUM_PAD_6			88
#  define NUM_PAD_7			89
#  define NUM_PAD_8			91
#  define NUM_PAD_9			92
#  define NUM_PAD_PLUS		69
#  define NUM_PAD_MINUS		78
#  define NUM_PAD_DEL		65
#  define NUM_PAD_MULTI		67
#  define NUM_PAD_DEVIDE	75
#  define A_KEY 			0
#  define S_KEY 			1
#  define D_KEY 			2
#  define W_KEY 			13
#  define Q_KEY 			12
#  define E_KEY 			14
# endif

#endif