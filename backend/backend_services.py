from flask import abort

def get_object_by_id(passed_id, passed_list):
    for obj in passed_list:
        if obj.obj_id == passed_id:
            return obj
    abort(404, description=f"'id: {passed_id}' not found")  