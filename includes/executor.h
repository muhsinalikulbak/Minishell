/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:21 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/16 03:03:43 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H


typedef enum e_exec_error
{
	EXEC_ERROR_CMD_NOT_FOUND,       // 127
	EXEC_ERROR_PERMISSION_DENIED,   // 126  
	EXEC_ERROR_FILE_NOT_FOUND,      // 1
	EXEC_ERROR_IS_DIRECTORY         // 126
}		t_exec_error;




#endif