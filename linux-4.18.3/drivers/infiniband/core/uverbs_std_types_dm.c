/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "uverbs.h"
#include <rdma/uverbs_std_types.h>

static int uverbs_free_dm(struct ib_uobject *uobject,
			  enum rdma_remove_reason why)
{
	struct ib_dm *dm = uobject->object;

	if (why == RDMA_REMOVE_DESTROY && atomic_read(&dm->usecnt))
		return -EBUSY;

	return dm->device->dealloc_dm(dm);
}

static int UVERBS_HANDLER(UVERBS_METHOD_DM_ALLOC)(struct ib_device *ib_dev,
						  struct ib_uverbs_file *file,
						  struct uverbs_attr_bundle *attrs)
{
	struct ib_ucontext *ucontext = file->ucontext;
	struct ib_dm_alloc_attr attr = {};
	struct ib_uobject *uobj;
	struct ib_dm *dm;
	int ret;

	if (!ib_dev->alloc_dm)
		return -EOPNOTSUPP;

	ret = uverbs_copy_from(&attr.length, attrs,
			       UVERBS_ATTR_ALLOC_DM_LENGTH);
	if (ret)
		return ret;

	ret = uverbs_copy_from(&attr.alignment, attrs,
			       UVERBS_ATTR_ALLOC_DM_ALIGNMENT);
	if (ret)
		return ret;

	uobj = uverbs_attr_get(attrs, UVERBS_ATTR_ALLOC_DM_HANDLE)->obj_attr.uobject;

	dm = ib_dev->alloc_dm(ib_dev, ucontext, &attr, attrs);
	if (IS_ERR(dm))
		return PTR_ERR(dm);

	dm->device  = ib_dev;
	dm->length  = attr.length;
	dm->uobject = uobj;
	atomic_set(&dm->usecnt, 0);

	uobj->object = dm;

	return 0;
}

static DECLARE_UVERBS_NAMED_METHOD(UVERBS_METHOD_DM_ALLOC,
	&UVERBS_ATTR_IDR(UVERBS_ATTR_ALLOC_DM_HANDLE, UVERBS_OBJECT_DM,
			 UVERBS_ACCESS_NEW,
			 UA_FLAGS(UVERBS_ATTR_SPEC_F_MANDATORY)),
	&UVERBS_ATTR_PTR_IN(UVERBS_ATTR_ALLOC_DM_LENGTH,
			    UVERBS_ATTR_TYPE(u64),
			    UA_FLAGS(UVERBS_ATTR_SPEC_F_MANDATORY)),
	&UVERBS_ATTR_PTR_IN(UVERBS_ATTR_ALLOC_DM_ALIGNMENT,
			    UVERBS_ATTR_TYPE(u32),
			    UA_FLAGS(UVERBS_ATTR_SPEC_F_MANDATORY)));

static DECLARE_UVERBS_NAMED_METHOD_WITH_HANDLER(UVERBS_METHOD_DM_FREE,
	uverbs_destroy_def_handler,
	&UVERBS_ATTR_IDR(UVERBS_ATTR_FREE_DM_HANDLE,
			 UVERBS_OBJECT_DM,
			 UVERBS_ACCESS_DESTROY,
			 UA_FLAGS(UVERBS_ATTR_SPEC_F_MANDATORY)));

DECLARE_UVERBS_NAMED_OBJECT(UVERBS_OBJECT_DM,
			    /* 1 is used in order to free the DM after MRs */
			    &UVERBS_TYPE_ALLOC_IDR(1, uverbs_free_dm),
			    &UVERBS_METHOD(UVERBS_METHOD_DM_ALLOC),
			    &UVERBS_METHOD(UVERBS_METHOD_DM_FREE));
newcodenewcodenewcodenewcodenewcodenewcodenewcode
